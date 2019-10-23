CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6226;
	title = 622602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 19;
			elnk = 255;
			nextlnk = 100;
			prelnk = "18;";

			CDboTSActSendSvrEvt
			{
				id = 407;
				tblidx = 6226;
				stradius = 0;
				stype = 2;
				taid = 1;
				ttype = 255;
				type = 6;
			}
		}
		CDboTSContGAct
		{
			cid = 102;
			elnk = 255;
			nextlnk = 254;
			prelnk = "101;";

			CDboTSActWorldPlayScript
			{
				sid = 6226;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 18;
			prelnk = "2;";

			CDboTSActWorldPlayScript
			{
				sid = 6226;
				start = 1;
				taid = 1;
				uof = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "3;2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 622614;
			nextlnk = 101;
			rwdtbl = 622601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "19;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3011101;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "102;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 622608;
			gtype = 4;
			oklnk = 2;
			area = 622601;
			goal = 622604;
			sort = 622605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 622602;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 622607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 43;
				minlvl = 35;
			}
			CDboTSClickNPC
			{
				npcidx = 3011101;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 622608;
				gtype = 4;
				area = 622601;
				goal = 622604;
				grade = 132203;
				rwd = 100;
				sort = 622605;
				stype = 2;
				taid = 1;
				title = 622602;
			}
			CDboTSActNPCConv
			{
				conv = 622609;
				ctype = 1;
				idx = 3011101;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1881101;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 102;
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
		CDboTSContGCond
		{
			cid = 18;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 19;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

