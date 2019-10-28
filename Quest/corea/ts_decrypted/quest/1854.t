CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1854;
	title = 185402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 185409;
				ctype = 1;
				idx = 4151206;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 185408;
				gtype = 2;
				area = 185401;
				goal = 185404;
				m0fz = "1503.000000";
				m0widx = 1;
				sort = 185405;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "2135.000000";
				m0ttip = 185415;
				rwd = 100;
				taid = 1;
				title = 185402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 1076;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 185407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4151206;
			}
			CDboTSCheckLvl
			{
				maxlvl = 48;
				minlvl = 40;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 185408;
			gtype = 2;
			oklnk = 2;
			area = 185401;
			goal = 185404;
			sort = 185405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 185402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 185414;
			nextlnk = 101;
			rwdtbl = 185401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151206;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 18;
				iidx = 1076;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1076;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 185407;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

