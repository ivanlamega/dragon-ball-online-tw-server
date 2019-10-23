CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 666;
	title = 66602;

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
				eitype = 0;
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
			stdiag = 66607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 66614;
			nextlnk = 101;
			rwdtbl = 66601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
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
				conv = 66609;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 66608;
				m1fx = "5421.000000";
				m2fz = "844.000000";
				m1fy = "0.000000";
				sort = 66605;
				m2widx = 1;
				grade = 132203;
				m0fx = "5686.000000";
				m0ttip = 66615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 66602;
				gtype = 2;
				area = 66601;
				goal = 66604;
				m0fz = "1112.000000";
				m0widx = 1;
				m1ttip = 66616;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "579.000000";
				m2fx = "6361.000000";
				m2ttip = 66617;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 5811108;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 66608;
			gtype = 2;
			oklnk = 2;
			area = 66601;
			goal = 66604;
			sort = 66605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66602;
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
				itype = 0;
			}
		}
	}
}

