CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1171;
	title = 117102;

	CNtlTSGroup
	{
		gid = 0;

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
				eitype = 3;
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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 117107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5533301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1170;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 117109;
				ctype = 1;
				idx = 5533301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 117108;
				m1fx = "130.000000";
				m2fz = "-338.000000";
				m1fy = "0.000000";
				sort = 117105;
				m2widx = 9;
				grade = 132203;
				m0fx = "213.000000";
				m0ttip = 117115;
				m1widx = 9;
				rwd = 100;
				taid = 1;
				title = 117102;
				gtype = 2;
				area = 117101;
				goal = 117104;
				m0fz = "-473.000000";
				m0widx = 9;
				m1ttip = 117115;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-480.000000";
				m2fx = "138.000000";
				m2ttip = 117115;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 996;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 117114;
			nextlnk = 101;
			rwdtbl = 117101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173110;
			}
			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 117108;
			gtype = 2;
			oklnk = 2;
			area = 117101;
			goal = 117104;
			sort = 117105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 117102;
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
				iidx0 = 996;
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
			stdiag = 117107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

