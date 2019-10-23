CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 975;
	title = 97502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 97509;
				ctype = 1;
				idx = 4751403;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 97508;
				m1fx = "2218.000000";
				m2fz = "1048.000000";
				m1fy = "0.000000";
				sort = 97505;
				m2widx = 1;
				grade = 132203;
				m0fx = "2150.000000";
				m0ttip = 97515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 97502;
				gtype = 1;
				area = 97501;
				goal = 97504;
				m0fz = "1183.000000";
				m0widx = 1;
				m1ttip = 97515;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1180.000000";
				m2fx = "1987.000000";
				m2ttip = 97515;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 737;
				cnt0 = 4;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
				itype = 3;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 97514;
			nextlnk = 101;
			rwdtbl = 97501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751403;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 97507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4751403;
			}
			CDboTSCheckLvl
			{
				maxlvl = 44;
				minlvl = 36;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;252;0;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 97508;
			gtype = 1;
			oklnk = 2;
			area = 97501;
			goal = 97504;
			sort = 97505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 97502;
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
	}
}

