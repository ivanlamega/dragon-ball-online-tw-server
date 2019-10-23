CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1312;
	title = 131202;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 131209;
				ctype = 1;
				idx = 1752103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 131208;
				m1fx = "1142.000000";
				area = 131201;
				goal = 131204;
				m0fz = "3710.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 131216;
				sort = 131205;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "3669.000000";
				grade = 132203;
				m0fx = "1175.000000";
				m0ttip = 131215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 131202;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 814;
				cnt0 = 24;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 131208;
			gtype = 2;
			oklnk = 2;
			area = 131201;
			goal = 131204;
			sort = 131205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 131202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 131214;
			nextlnk = 101;
			rwdtbl = 131201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 24;
				iidx = 814;
			}
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
			stdiag = 131207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
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
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 814;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 814;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 131207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

