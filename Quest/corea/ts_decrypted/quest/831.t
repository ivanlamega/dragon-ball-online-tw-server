CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 831;
	title = 83102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 83109;
				ctype = 1;
				idx = 4511605;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 83108;
				gtype = 1;
				area = 83101;
				goal = 83104;
				grade = 132203;
				rwd = 100;
				sort = 83105;
				stype = 2;
				taid = 1;
				title = 83102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 83108;
			gtype = 1;
			oklnk = 2;
			area = 83101;
			goal = 83104;
			sort = 83105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 83102;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 83114;
			nextlnk = 254;
			rwdtbl = 83101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 83107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511605;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

